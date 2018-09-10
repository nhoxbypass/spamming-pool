// Week04 WAD Assignment

//Declare variable
function onOperatorClick(id, radioButtons) {
    for (var i = 0; i < radioButtons.length; i++) {
        if (radioButtons.item(i).id != id) {
            radioButtons.item(i).checked = false;
        }
        else {
            //This is the clicked radio button that trigger this event
            //Ignore
        }
    }
}


function isValidInput(input) {
    return !isNaN(input);
}

//Handle mouse out event
function onMouseOut(id) {
    if (document.getElementById(id).value != "") {
        if (!isValidInput(document.getElementById(id).value)) {
            document.getElementById("calc_button").disabled = true;
            if (id == "first_input")
                document.getElementById("error_msg").innerHTML = "Giá trị nhập ở ô <i>số thứ nhất</i> không phải số thực!";
            else if (id == "second_input")
                document.getElementById("error_msg").innerHTML = "Giá trị nhập ở ô <i>số thứ hai</i> không phải số thực!";
        }
        else {
            document.getElementById("calc_button").disabled = false;
            document.getElementById("error_msg").innerHTML = "";
        }
    }
}


//Main program
$(document).ready(function () {
    //Local variables
    var first_input, second_input, rb_add, rb_sub, rb_mul, rb_div;
    var inputs = document.getElementsByClassName("input");
    var radioButtons = document.getElementsByClassName("operator-button");

    //Add event handler for elements
    for (var i = 0; i < inputs.length; i++) {
        inputs.item(i).addEventListener("mouseout", function () {
            onMouseOut(this.id)
        });
    }

    Array.prototype.forEach.call(radioButtons, function (button) {
        // Do stuff here
        button.addEventListener("click", function () {
            onOperatorClick(this.id, radioButtons)
        })
    });


    //Calculation button event handler
    $("#calc_button").click(function () {
        //Get input value
        first_input = $("#first_input").val();
        second_input = $("#second_input").val();
        rb_add = document.getElementById("button_add").checked;
        rb_sub = document.getElementById("button_sub").checked;
        rb_mul = document.getElementById("button_mul").checked;
        rb_div = document.getElementById("button_div").checked;

        $.post("http://localhost:3000", {
            first_input: first_input,
            second_input: second_input,
            rb_add: rb_add,
            rb_sub: rb_sub,
            rb_mul: rb_mul,
            rb_div: rb_div
        }, function (res) {
            document.getElementById("result").value = "";
            document.getElementById("error_msg").innerHTML = "";

            if (isValidInput(res)) {
                document.getElementById("result").value = res;
            }
            else {
                document.getElementById("error_msg").innerHTML = res;
            }
        });
    });
});   




