<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
       $IdEquipe= $_POST['IdEquipe'];
$result = mysqli_query($con,"SELECT IdPDM FROM forme WHERE IdEquipe='$IdEquipe'");
echo "<Nest>";
while($row = mysqli_fetch_array($result))
 {
 	$curs=$row['IdPDM'];
 	$nresult = mysqli_query($con,"SELECT * FROM PDM WHERE IdPDM='$curs'");
while($nrow = mysqli_fetch_array($nresult))
 {
  echo "<PDM>";
  echo "<IdPDM>" . $nrow['IdPDM'] . "</IdPDM>" ;
  echo "<NomPDM>" . $nrow['NomPDM'] . "</NomPDM>" ;
  echo "<PrenomPDM>" . $nrow['PrenomPDM'] . "</PrenomPDM>" ;
  echo "</PDM>";	
}
}
 echo "</Nest>";
mysqli_close($con);
?>