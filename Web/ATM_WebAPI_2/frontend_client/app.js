const express = require('express'),
    morgan = require('morgan'),
    path = require('path');

var dashboard = require('./routes/dashboard');
var history = require('./routes/history');
var transfer = require('./routes/transfer');
var withdraw = require('./routes/withdraw');
var userInfo = require('./routes/user_info');
var internal_transfer = require('./routes/internal_transfer');

let app = express();

app.use(morgan('dev'));

app.use(express.static(
    path.resolve(__dirname, 'public')
));

app.use('/dashboard', dashboard);
app.use('/history', history);
app.use('/transfer', transfer);
app.use('/withdraw', withdraw);
app.use('/user_info', userInfo);
app.use('/internal_transfer', internal_transfer);

app.get('/', (req, res) => {
    res.sendFile('index.html', {
        root: path.join(__dirname, '../public')
    });
});

const PORT = 3001;
app.listen(PORT, () => {
    console.log('client-site run on port: ' + PORT);
});