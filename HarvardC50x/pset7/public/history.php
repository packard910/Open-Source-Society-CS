<?php

// configuration
require("../includes/config.php");

// if session log transaction variable not set, initialize
if (!isset($_SESSION["log_transaction"]))
{
    $_SESSION["log_transaction"] = false;
}

// if accessed by GET method display history for user
if (($_SERVER["REQUEST_METHOD"] == "GET") && ($_SESSION["log_transaction"] == false))
{
    // get complete list of user transactions
    $log_query = query("SELECT * FROM log WHERE id = ?", $_SESSION["id"]);

    // render history form
    if ($log_query == false)
    {
	render("history_form.php", ["title" => "History"]);
    }
    else
    {
	render("history_form.php", ["title" => "History","log" =>$log_query]);
    }    
}

// transaction waiting to be logged
else if (($_SERVER["REQUEST_METHOD"] == "GET")  && ($_SESSION["log_transaction"] == true))
{
    // components of log entry
    $id = $_SESSION["id"];
    $transaction = $_SESSION["transaction"];
    $date = date("n/j/y, g:i a");
    $symbol = $_SESSION["symbol"];
    $shares = $_SESSION["shares"];
    $price = $_SESSION["price"];
    $total = $_SESSION["total"];

    // add transaction to history database
    query("INSERT INTO log (id, transaction, date, symbol, shares, price, total) VALUES (?,?,?,?,?,?,?)",$id,$transaction,$date,$symbol,$shares,$price,$total);

    // reset transaction flag
    $_SESSION["log_transaction"] = false;

    // redirect to index.php
    redirect("index.php");
}

?>
