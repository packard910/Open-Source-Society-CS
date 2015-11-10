<?php

// configuration
require("../includes/config.php");

// if accessed by GET method render sell menu
if ($_SERVER["REQUEST_METHOD"] == "GET")
{
    // get list of all owned stock symbols from database
    $symbol_query = query("SELECT symbol FROM shares WHERE id=?",$_SESSION["id"]);
    $symbol_list = [];
    foreach($symbol_query as $index=>$queryitem)
    {
	$symbol_list[$index] = $queryitem["symbol"];
    }

    // render form using list of owned symbols
    render("sell_form.php",["title" => "Sell Stocks","symbols" => $symbol_list]);
}

// if accessed by POST method sell stocks
else if($_SERVER["REQUEST_METHOD"] == "POST")
{
    // ensure that user input is safe
    $_POST["shares"] = htmlspecialchars($_POST["shares"]);

    // ensure that a symbol was selected
    if(!isset($_POST["symbol"]))
    {
	apologize("You must select a symbol from the drop-down menu");
    }

    // get current number of shares owned
    $query_shares = query("SELECT shares FROM shares WHERE id=? AND symbol=?",$_SESSION["id"],$_POST["symbol"]);
    $current_shares = $query_shares[0]["shares"];
    // round input number of shares to check if integer
    $roundshares = floor($_POST["shares"]);

    // get current stock price and determine cash from sale
    $query_price = lookup($_POST["symbol"]);
    $current_price = $query_price["price"];
    $cash_added = $current_price * $_POST["shares"];

    // ensure not selling more shares than currently owned
    if ($_POST["shares"] > $current_shares)
    {
	apologize("You cannot sell more shares than you own");
    }
    // ensure number of shares sold is an integer    
    else if ($_POST["shares"] != $roundshares)
    {
	apologize("You can only sell an integer number of shares");
    }
    // ensure not selling a negative number of shares
    else if ($_POST["shares"] < 1)
    {
	apologize("You cannot sell a non-positive number of shares - try buying instead");
    }
    // remove requested number of shares and update cash
    else
    {
	// remove shares from user portfolio
	$final_shares = $current_shares - $_POST["shares"];
	if ($final_shares == 0)
        {
	    query("DELETE FROM shares WHERE id=? AND symbol=?",$_SESSION["id"],$_POST["symbol"]);
	}
   	else
	{
	    query("UPDATE shares SET shares=? WHERE id=? AND symbol=?",$final_shares,$_SESSION["id"],$_POST["symbol"]);
	}

	// add sale price to user cash
	query("UPDATE users SET cash=cash+? WHERE id=?",$cash_added,$_SESSION["id"]);

	// send transaction data to history.php
	$_SESSION["log_transaction"] = true;
	$_SESSION["transaction"] = "SELL";
	$_SESSION["symbol"] = $_POST["symbol"];
	$_SESSION["shares"] = $_POST["shares"];
	$_SESSION["price"] = $current_price;
        $_SESSION["total"] = $cash_added;
	redirect("history.php");
    }
}
?>
