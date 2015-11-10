<?php

// configuration
require("../includes/config.php");

// if page arrived at by GET reuqest stock symbol
if ($_SERVER["REQUEST_METHOD"] == "GET")
{
	render ("quote_submit_form.php", ["title" => "Get Quote"]);
}

// once form submitted, report stock price
else if ($_SERVER["REQUEST_METHOD"] == "POST")
{
	// ensure that user input is safe
	$_POST["symbol"] = htmlspecialchars($_POST["symbol"]);

	// check that form was submitted correctly
	if (empty($_POST["symbol"]))
	{
		apologize("You did not enter a stock symbol");
	}

	// obtain stock price 
	$stock = lookup($_POST["symbol"]);

	// apologize if lookup fails	
	if($stock === false)
	{
		apologize("Symbol not found");
	}
	
	// report stock price
	else
	{
		render("quote_report_form.php", ["title" => "Quote", "symbol" => $stock["symbol"], "name" => $stock["name"], "price" => $stock["price"]]);
	} 
}
?>
