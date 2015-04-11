<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
       $IdPDM= $_POST['Id'];
$result = mysqli_query($con,"SELECT * FROM PDM");
echo "<Nest>";
while($row = mysqli_fetch_array($result))
 {
  echo "<PDM>";
  echo "<IdPDM>" . $row['IdPDM'] . "</IdPDM>" ;
  echo "<NomPDM>" . $row['NomPDM'] . "</NomPDM>" ;
  echo "<PrenomPDM>" . $row['PrenomPDM'] . "</PrenomPDM>" ;
  echo "</PDM>";
 }
 echo "</Nest>";

mysqli_close($con);
?>