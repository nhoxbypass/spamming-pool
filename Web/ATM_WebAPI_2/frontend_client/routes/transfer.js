var express = require('express');
var router = express.Router();
var path = require('path');


router.get('/', (req, res) => {
     res.sendFile('transfer.html', {
        root: path.join(__dirname, '../public')
    });
});

module.exports = router;