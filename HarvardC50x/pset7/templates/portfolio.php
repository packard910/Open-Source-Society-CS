<div id="user_portfolio">
    <div class="portfolio-table">
    <table>
	<tr>
	    <th class="symbolHd">Symbol</th>
	    <th class="nameHd">Name</th>
	    <th class="sharesHd">Shares</th>
	    <th class="priceHd">Price</th>
	    <th class="totalHd">Total</th>               
        </tr>
	<?php	    
	    if (!empty($portfolio))
	    {
		foreach ($portfolio as $row)
 	        {
		    print("<tr>");
         	    print("<td class=\"symbol\">".$row["symbol"]."</td>");
	            print("<td class=\"name\">".$row["name"]."</td>");
		    print("<td class=\"shares\">".$row["shares"]."</td>");
		    print("<td class=\"price\">$".number_format($row["price"],2)."</td>");
                    print("<td class=\"total\">$".number_format($row["total"],2)."</td>");
		    print("</tr>");
	        }
                print("<tr>");
      		    print("<td class=\"totalname\">STOCK VALUE</td>");
		    print("<td></td>");
		    print("<td></td>");
		    print("<td></td>");
		    print("<td class=\"totalamt\">$".number_format($value,2)."</td>");
                print("</tr>");
            }
	    print("<tr>");
      		print("<td class=\"totalname\">CASH</td>");
		print("<td></td>");
		print("<td></td>");
		print("<td></td>");
		print("<td class=\"totalamt\">$".number_format($cash,2)."</td>");
            print("</tr>");
	?>
    </table> 
    </div>    
</div>
