<?php

// configuration
require("../includes/config.php");

// if accessed by GET method display buy menu
if ($_SERVER["REQUEST_METHOD"] == "GET")
{
    render("buy_form.php", ["title" => "Buy"]);
}

// if accessed by POST method execute buy
else if ($_SERVER["REQUEST_METHOD"] == "POST")
{
    // ensure that user input is safe
    $_POST["symbol"] = htmlspecialchars($_POST["symbol"]);
    $_POST["shares"] = htmlspecialchars($_POST["shares"]);

    // put symbol in standard form
    $symbol = strtoupper($_POST["symbol"]);

    // look up symbol and get quote on price
    $stock = lookup($symbol);

    // apologize if lookup fails	
    if($stock === false)
    {
	apologize("Symbol not found");
    }

    // find current amount of cash held by user
    $query_cash = query("SELECT cash FROM users WHERE id=?",$_SESSION["id"]);
    $cash = $query_cash[0]["cash"];

    // find total cost of shares
    $cost = ($_POST["shares"] * $stock["price"]);

    // check if buy request is valid
    if (preg_match("/^\d+$/", $_POST["shares"])!=1)
    {
  	apologize("You did not enter a valid number of shares");
    }
    // check if user has enough cash to buy shares
    else if ($cash < $cost)
    {
	apologize("You do not have enough cash to buy these shares");
    }
    // otherwise execute buy
    else
    {
	// add a new row to shares database if necessary
        if (query("SELECT shares FROM shares WHERE id=? AND symbol=?",$_SESSION["id"],$symbol)==false)
	{
	    query("INSERT INTO shares (id, symbol, shares) VALUES (?,?,?)",$_SESSION["id"],$symbol,$_POST["shares"]);
	}
	// otherwise add to current row        
        else
 	{
	    query("UPDATE shares SET shares=shares+? WHERE id=? AND symbol=?",$_POST["shares"],$_SESSION["id"],$symbol);
	}

        // deduct cash for sale
        query("UPDATE users SET cash=cash-? WHERE id=?",$cost,$_SESSION["id"]);

	// send transaction data to history.php
	$_SESSION["log_transaction"] = true;
	$_SESSION["transaction"] = "BUY";
	$_SESSION["symbol"] = $symbol;
	$_SESSION["shares"] = $_POST["shares"];
	$_SESSION["price"] = $stock["price"];
	$_SESSION["total"] = $cost;
	redirect("history.php");
    }
}

?>
