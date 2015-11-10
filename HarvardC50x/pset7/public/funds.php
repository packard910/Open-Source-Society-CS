<?php

// configuration
require("../includes/config.php");

// if accessed by GET method display buy menu
if ($_SERVER["REQUEST_METHOD"] == "GET")
{
    render("funds_form.php", ["title" => "Funds"]);
}

// if accessed by GET method display buy menu
if ($_SERVER["REQUEST_METHOD"] == "POST")
{
    // if user clicks deposit button
    if ($_POST["transfer"] == "deposit")
    {
	// ensure that user input is safe
	$_POST["deposit"] = htmlspecialchars($_POST["deposit"]);

	// ensure user entered a number
	if (!filter_var($_POST["deposit"],FILTER_VALIDATE_FLOAT))
	{
	    apologize("Your deposit must be a number");
	}
        // ensure deposit amount is positive
        else if ($_POST["deposit"] <= 0)
	{
	    apologize("Your deposit must be a postive number");
	}
        // deposit funds in account
        else
	{
	    query("UPDATE users SET cash=cash+? WHERE id=?",$_POST["deposit"],$_SESSION["id"]);
	    // information for history log
	    $_SESSION["transaction"] = "DEPOSIT";
            $_SESSION["total"] = $_POST["deposit"];
	}
    }	

    // otherwise user clicked withdraw button
    else if ($_POST["transfer"] == "withdraw")
    {
	// ensure that user input is safe
	$_POST["withdraw"] = htmlspecialchars($_POST["withdraw"]);

	// find out how much cash is in user account
 	$cash_query = query("SELECT cash FROM users WHERE id=?",$_SESSION["id"]);
	$user_cash = $cash_query[0]["cash"];

	// ensure user entered a number
	if (!filter_var($_POST["withdraw"],FILTER_VALIDATE_FLOAT))
	{
	    apologize("Your deposit must be a number");
	}
        // ensure deposit amount is positive
        else if ($_POST["withdraw"] <= 0)
	{
	    apologize("Your deposit must be a postive number");
	}
	// ensure that user can withdraw this amount
	else if ($_POST["withdraw"] > $user_cash)
	{
	    apologize("You are trying to withdraw more cash than you have");
	}
        // deposit funds in account
        else
	{
	    query("UPDATE users SET cash=cash-? WHERE id=?",$_POST["withdraw"],$_SESSION["id"]);
	    // information for history log
            $_SESSION["transaction"] = "WITHDRAW";
            $_SESSION["total"] = $_POST["withdraw"];
	}
    }
    else
    {
	apologize("Your transaction is invalid");
    }

    // send transaction information to history.php
    $_SESSION["log_transaction"] = true;
    $_SESSION["symbol"] = "Cash";
    $_SESSION["shares"] = "";
    $_SESSION["price"] = 0;
    redirect("history.php");
}

?>
