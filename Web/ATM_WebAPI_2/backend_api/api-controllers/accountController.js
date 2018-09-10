const express = require('express'),
    db = require('../fn/mysql-db');

let r = express.Router();
var gAccountId = "";
let MIN_BALANCE = 100000;
let TRANSFER_FEE_SAME_BANK = 3300;
let TRANSFER_FEE = 11000;


/*
 * GET methods
 *
 */

r.get('/', (req, res) => {
    res.statusCode = 400;
    res.end('Bad request!')
});

//Get all user info
r.get('/user_info', (req, res) => {
    var currentAcc = req.app.locals.currentAcc;

    if (currentAcc != null) {
        res.statusCode = 200;
        res.json(currentAcc);
    } else {
        let obj = {
            message: 'Unauthorized! Please login first!'
        };
        res.statusCode = 401;
        res.json(obj);
    }
});

r.get('/banks', (req, res) => {
    const sql = 'select * from bank';
    db.load(sql).then(rows => {
        req.app.locals.banks = rows;
        res.json(rows);
    });
});

r.get('/withdraw', (req, res) => {
    if (req.app.locals.currentAcc != null) {
        gAccountId = req.app.locals.currentAcc.account_id;

        if (gAccountId != '' && gAccountId != null && gAccountId != undefined) {
            res.statusCode = 200;
            let obj = {
                message: 'Succeed'
            };
            res.json(obj);
            return;
        }
    } 

    res.statusCode = 401;
    res.end("Unauthorized! Please login first!");
});


r.get('/transfer', (req, res) => {
    if (req.app.locals.currentAcc != null) {
        gAccountId = req.app.locals.currentAcc.account_id;

        if (gAccountId != '' && gAccountId != null && gAccountId != undefined) {
            res.statusCode = 200;
            let obj = {
                message: 'Succeed'
            };
            res.json(obj);
            return;
        }
    } 

    res.statusCode = 401;
    res.end("Unauthorized! Please login first!");
});

//Get current balance of user
r.get('/balance', (req, res) => {
    if (req.app.locals.currentAcc != null) {
        gAccountId = req.app.locals.currentAcc.account_id;

        if (gAccountId != '' && gAccountId != null && gAccountId != undefined) {
            let sql = `SELECT balance FROM account WHERE account_id = ` + gAccountId;
            db.load(sql).then(rows => {
                res.statusCode = 200;
                res.json(rows[0]);
            });

            return;
        }
    } 

    let obj = {
        message: 'Unauthorized! Please login first!'
    };
    res.statusCode = 401;
    res.json(obj);
});


//Get transaction history
r.get('/history', (req, res) => {
    if (req.app.locals.currentAcc != null) {
        gAccountId = req.app.locals.currentAcc.account_id;

        if (gAccountId != '' && gAccountId != null && gAccountId != undefined) {
            let startTime = req.query.startTime;
            let endTime = req.query.endTime;

            let sql = `SELECT * FROM history WHERE (sender_id=` + gAccountId + ` OR receiver_id=` + gAccountId + `)`;
            if (startTime != undefined) {
                sql = sql + ` AND transaction_id>=` + startTime;
            }
            if (endTime != undefined) {
                sql = sql + ` AND transaction_id<=` + endTime;
            }

            console.log(sql);
           
            db.load(sql).then(rows => {
                req.app.locals.banks = rows;
                res.json(rows);
            });

            return;
        }
    } 

    let obj = {
        message: 'Unauthorized! Please login first!'
    };
    res.statusCode = 401;
    res.json(obj);
});





/*
 * POST methods
 *
 */

//login
r.post('/login', (req, res) => {
    let id = req.query.account_id;
    let pin = req.query.pinCode;

    console.log("id: "+ id);
    console.log("pin: "+ pin);

    let sql = `SELECT * FROM account WHERE account_id=` + id + ` AND pin=` + pin;
    db.load(sql).then(val => {
        if (val.length > 0) {
            //Succeed
            let jsonVal = JSON.parse(JSON.stringify(val[0]));
            req.app.locals.currentAcc = val[0];
            gAccountId = jsonVal.account_id;
            res.statusCode = 200;
            res.json(req.app.locals.currentAcc);
        } else {
        	//Failed
            gAccountId = '';
            req.app.locals.currentAcc = null;

			res.statusCode = 200;
            console.log("failed");
        	res.json(null); 
        }

        
    });
});

r.get('/isLogined', (req, res) => {

    if (req.app.locals.currentAcc != null){
        let obj = {
        message: 'success'
        };
        res.json(obj);    
    }else{
        let obj = {
        message: 'fail'
        };
        res.json(obj);
    }
    
});


//withdraw money from bank account
r.post('/withdraw', (req, res) => {
    gAccountId = req.app.locals.currentAcc.account_id;
    if (req.app.locals.currentAcc != null) {
        //Check withdraw amount 
        let amount = +req.query.amount;

        if (amount % 50000 == 0) {
            //multiple of 50000 -> allow withdraw

            let currBalance = req.app.locals.currentAcc.balance;
            console.log("****"+currBalance);

            if (currBalance - amount >= MIN_BALANCE) {
                    //TODO: Add Transaction
                currBalance = currBalance - amount ;

                req.app.locals.currentAcc.balance = currBalance;

                let balanceSQL = `UPDATE account SET balance=` + currBalance + ` WHERE account_id=` + gAccountId;
                db.load(balanceSQL).then(val => { 
                    //Insert to transaction history
                    //Use transaction_id as timestamp for db has "row locking" features so that there is no transaction at the same time
                    let time = new Date();
                    let timestring = time.toString();
                    let historySQL = `INSERT INTO history(transaction_id, sender_id, receiver_id, amount, time,fee) VALUES(` + Date.now() + `,` + gAccountId + `, null, ` + amount +',"'+ timestring+  `",0)`;
                    db.insert(historySQL).then(val => {
                        console.log(val);
                        let obj = {
                            message: "Take your money [̲̅$̲̅(̲̅"+ amount + ")̲̅$̲̅] ... Thank you for using our services!"
                        };
                        res.json(obj);
                        //End transaction
                    });        
                })
            } else {
                let obj = {
                    message: 'Not enough money to withdraw!'
                };
                res.json(obj);
                    
            } 
        } else {
            let obj = {
                message: `The withdraw amount must be multiple of 50,000! Currently:` + amount
            };
            res.json(obj);
        }
    } else {
        res.statusCode = 401;
        res.end("");
        let obj = {
            message: "Unauthorized! Please login first!"
        };
        res.json(obj);
    }
});




//transfer money from bank account to others
r.post('/transfer', (req, res) => {
    if (req.app.locals.currentAcc != null) {
        let receiverAccId = req.query.receiverAccId;
        let amount = +req.query.amount;
        let isSameBank = req.query.sameBank;

        let transferFee = TRANSFER_FEE;
        let currBankId = req.app.locals.currentAcc.bank_id;

        //-1: the same. 
        //others is not
        if (isSameBank == -1) {
            transferFee = TRANSFER_FEE_SAME_BANK;
        }else{

            currBankId = req.app.locals.banks[isSameBank].bank_id;
        }


            let currBalance = req.app.locals.currentAcc.balance;

            console.log("currBankId: "+ currBankId);
            if (currBalance - amount - transferFee >= MIN_BALANCE) {
                //Ready to transfer

                var receiverBalanceSQL = `SELECT balance FROM account WHERE account_id=` + receiverAccId + ` and bank_id=${currBankId}`;
                db.load(receiverBalanceSQL).then(val => {
                    json = JSON.parse(JSON.stringify(val[0]));

                    let receiverBalance = +json.balance;


                    //TODO: Add Transaction
                    receiverBalance = receiverBalance + amount;
                    currBalance = currBalance - amount - transferFee;
                    req.app.locals.currentAcc.balance = currBalance;

                    //Update in db
                    let balanceSQL = `UPDATE account SET balance=` + currBalance + ` WHERE account_id=` + gAccountId;
                    receiverBalanceSQL = `UPDATE account SET balance=` + receiverBalance + ` WHERE account_id=` + receiverAccId;

                    db.load(balanceSQL).then(val => {
                        db.load(receiverBalanceSQL).then(val => {
                            //Succeed
                            //Insert to transaction history
                            //Use transaction_id as timestamp for db has "row locking" features so that there is no transaction at the same time
                            let time = new Date();
                            let timestring = time.toString();
                            let historySQL = `INSERT INTO history(transaction_id, sender_id, receiver_id, amount,time,fee) VALUES(` + Date.now() + `,` + +gAccountId + `, ` + receiverAccId + `, ` + amount +',"'+ timestring+  `"`+','+ transferFee +`)`;
                            console.log(historySQL)
                            db.insert(historySQL).then(val => {
                            
                            
                                let obj = {
                                    message: "Transaction complete. [̲̅$̲̅(̲̅"+ amount + ")̲̅$̲̅] has been transfer to " + receiverAccId + "... Thank you for using our services!"
                                };
                                res.json(obj);
                            });

                        });
                    });
                });
        
            }   else {
                    
                    let obj = {
                        message: "Not enough money to withdraw!"
                    };
                    res.json(obj);
                }   
            
      } else {
        res.statusCode = 401;
        res.end("Unauthorized! Please login first!");
    }
});



module.exports = r;