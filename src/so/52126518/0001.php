<?php 
  if(isset($_GET['edit'])) {
    $res_hed = $mysqli->query("select VAT FROM CUSTOMERS WHERE id=$_GET[edit]");

    for ($row_no = $res_hed->num_rows - 1; $row_no >= 0; $row_no--) {
      $VAT = $row['VAT'];
    }

    echo "
<form class='col-md-3' method='GET'>
<h3>Edit VAT</h3>
<div class='form-group'>
<label>VAT</label>
<input class='form-control' type='text' name='VAT' value=$VAT>
</div>" // this quote was missing
  } // this bracket was in the wrong place
?>      
