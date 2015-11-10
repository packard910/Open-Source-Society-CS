<?php

    // configuration
    require("../includes/config.php"); 

    // gather basic information about user portfolio
    $portfolio = query("SELECT * FROM shares WHERE id = ?",$_SESSION["id"]);
    $query_cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    $cash = $query_cash[0]["cash"];

    // if portfolio empty render with only cash
    if ($portfolio === false)
    {
	render("portfolio.php", ["title" => "Portfolio", "cash" => $cash]);
    }
    
    // else prepare porfolio array to be rendered
    else
    { 
        // get price of each stock and append to portfolio array	 
        $value = 0.00;	
        foreach($portfolio as $index => $row)
        {
	    $stock_lookup = lookup($row["symbol"]);
            $portfolio[$index]["name"] = $stock_lookup["name"];
	    $portfolio[$index]["price"] = $stock_lookup["price"];
	    $portfolio[$index]["total"] = $row["shares"] * $portfolio[$index]["price"];
            $value += $portfolio[$index]["total"]; 
    	}

        // render portfolio
    	render("portfolio.php", ["title" => "Portfolio", "portfolio" => $portfolio, "value" => $value, "cash" => $cash]);
    }
?>
