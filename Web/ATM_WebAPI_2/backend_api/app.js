const express = require('express'),
    morgan = require('morgan'),
    bodyParser = require('body-parser');

const accountApiController = require('./api-controllers/accountController');
const PORT = 3000;

let app = express();

app.use(morgan('dev'));
app.use(bodyParser.json()); // support json encoded bodies
app.use(bodyParser.urlencoded({ extended: true })); // support encoded bodies

app.use((req, res, next) => {
    res.header('Access-Control-Allow-Credentials', true);
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE');
    res.header('Access-Control-Allow-Origin', 'http://localhost:3001');
    res.header('Access-Control-Allow-Headers', 'Origin, X-Requested-With, Content-Type, Accept');
    next();
});

app.use('/account', accountApiController);

app.get('/', (req, res) => {
    let obj = {
        message: 'hello'
    };
    res.json(obj);
});

app.locals.currentAcc = null;
app.locals.banks = null;

app.listen(PORT, () => {
    console.log('api run on port: ' + PORT);
});