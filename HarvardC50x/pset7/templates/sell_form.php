<form action="sell.php" method="post">
    <fieldset>
	<div class="form-group">
            <select autofocus class="form-control" name="symbol">
	        <option value="" disabled selected>Symbols</option>
	    <?php
 		foreach($symbols as $symbol)
		{
		    print("<option value=\"".$symbol."\">".$symbol."</option>");
		}
            ?>
	    </select>
        </div>
        <div class="form-group">
            <input autofocus class="form-control" style="width: 15%" name="shares" placeholder="Shares" type="text" autocomplete="off"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Sell</button>
        </div>
    </fieldset>
</form>
