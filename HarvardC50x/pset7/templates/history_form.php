<div id="user_portfolio">
    <div class="history-table">
    <table>
	<tr>
	    <th class="hist">Transaction</th>
	    <th class="histdate">Date/Time</th>
	    <th class="hist">Symbol</th>
            <th class="hist">Shares</th>
            <th class="hist">Price</th>
	    <th class="hist">Total</th>
        </tr>
	<?php   
	    if (!empty($log))
	    {
		foreach ($log as $row)
 	        {
		    print("<tr>");
         	    print("<td class=\"hist\">".$row["transaction"]."</td>");
	            print("<td class=\"histdate\">".$row["date"]."</td>");
		    print("<td class=\"hist\">".$row["symbol"]."</td>");
		    print("<td class=\"hist\">".$row["shares"]."</td>");
                    print("<td class=\"hist\">$".number_format($row["price"],2)."</td>");
		    print("<td class=\"hist\">$".number_format($row["total"],2)."</td>");
		    print("</tr>");
	        }
   	    }
	?>
    </table> 
    </div>    
</div>
