var express = require("express");
var app = express();
var bodyParser = require("body-parser");

app.use(express.static(__dirname + '/public'));
app.use(bodyParser.urlencoded({extended: false}));
app.use(bodyParser.json());


app.get("/", function (req, res) {
    res.sendFile(__dirname + "/public/index.html");
});


app.post('/', function (req, res) {
    var first_number = req.body.first_input;
    var second_number = req.body.second_input;
    var result = "";
    if (isNaN(first_number)) {
        res.end("Giá trị nhập ở ô số thứ nhất không phải số thực!");
    } else if (first_number == "") {
        error = "Giá trị nhập ở ô số thứ nhất rỗng!";
        res.end(error);
    } else if (isNaN(second_number)) {
        error = "Giá trị nhập ở ô số thứ hai không phải số thực!";
        res.end(error);
    } else if (second_number == "") {
        error = "Giá trị nhập ở ô số thứ hai rỗng!";
        res.end(error);
    } else if (req.body.rb_add == "true") {
        result = (parseFloat(first_number) + parseFloat(second_number)).toString();
        res.end(result);
    } else if (req.body.rb_sub == "true") {
        result = (parseFloat(first_number) - parseFloat(second_number)).toString();
        res.end(result);
    } else if (req.body.rb_mul == "true") {
        result = (parseFloat(first_number) * parseFloat(second_number)).toString();
        res.end(result);
    } else if (req.body.rb_div == "true") {
        result = (parseFloat(first_number) / parseFloat(second_number)).toString();
        res.end(result);
    } else {
        res.end("Không có phép tính nào được chọn!");
    }
});


app.listen(3000, function () {
    console.log("Server started on localhost with port 3000");
})
