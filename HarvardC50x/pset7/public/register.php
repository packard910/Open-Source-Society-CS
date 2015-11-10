<?php

// configuration
require("../includes/config.php");

// if user reached page via GET (as by clicking a link or via redirect)
if ($_SERVER["REQUEST_METHOD"] == "GET")
{
	// else render form
	render ("register_form.php", ["title" => "Register"]);
}

// else if user reached page via POST (as by submitting a form via POST)
else if ($_SERVER["REQUEST_METHOD"] == "POST")
{
	// ensure that user input is safe
	$_POST["username"] = htmlspecialchars($_POST["username"]);
	$_POST["password"] = htmlspecialchars($_POST["password"]);
	$_POST["confirmation"] = htmlspecialchars($_POST["confirmation"]);

	// check that form was submitted correctly
	if (empty($_POST["username"]))
	{
		apologize("You did not enter a username");
	}
	else if (empty($_POST["password"]))
	{
		apologize("You did not enter a password");
	}
	else if ($_POST["password"] != $_POST["confirmation"])
	{
		apologize("The password and confirmation field do not match");
	}

	// register new user
	else 
	{
		if(query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], crypt($_POST["password"])) === false)
		{
			apologize("Registration failed - username may already be in use");
		}
		else
		{
			$rows = query("SELECT LAST_INSERT_ID() AS id");
			$id = $rows[0]["id"];
			$_SESSION["id"] = $id;
			redirect("index.php");
		}
	}
}

?>
