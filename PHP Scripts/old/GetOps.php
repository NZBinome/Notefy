<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
       $IdRapport= $_POST['IdRapport'];
$result = mysqli_query($con,"SELECT IdOp,Remarque,Gravite FROM contient WHERE IdRapport='$IdRapport'");
echo "<Nest>";
while($row = mysqli_fetch_array($result))
 {
 	$Op=$row['IdOp'];
 	$nresult = mysqli_query($con,"SELECT DescOp,DA FROM Operations WHERE IdOp='$Op'");
while($nrow = mysqli_fetch_array($nresult))
 {
  echo "<Operations>";
  echo "<IdOperations>" . $Op . "</IdOperations>" ;
  echo "<Remarque>" . $row['Remarque'] . "</Remarque>" ;
  echo "<Gravite>" . $row['Gravite'] . "</Gravite>" ;
  echo "<DescOp>" . $nrow['DescOp'] . "</DescOp>" ;
  echo "<DA>" . $nrow['DA'] . "</DA>" ;
  echo "</Operations>";	
}
}
 echo "</Nest>";
mysqli_close($con);
?>