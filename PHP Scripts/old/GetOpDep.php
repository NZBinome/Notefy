<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
   $Id= $_POST['Id'];

 	$nresult = mysqli_query($con,"SELECT * FROM Operations WHERE DA='Depart'");
  echo "<Nest>" ;
while($row = mysqli_fetch_array($nresult))
 {
  echo "<Operations>";
  echo "<IdOperations>" . $row['IdOp'] . "</IdOperations>" ;
  echo "<DescOp>" . $row['DescOp'] . "</DescOp>" ;
  echo "<DA>" . $row['DA'] . "</DA>" ;
  echo "</Operations>";	
}
 echo "</Nest>";
mysqli_close($con);
?>