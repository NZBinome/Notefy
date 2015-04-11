<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
       $IdEq= $_POST['IdEq'];
$result = mysqli_query($con,"SELECT IdEDL FROM forme2 WHERE IdEq='$IdEq'");
echo "<Nest>";
while($row = mysqli_fetch_array($result))
 {
 	$curs=$row['IdEDL'];
 	$nresult = mysqli_query($con,"SELECT * FROM EDL WHERE IdEDL='$curs'");
while($nrow = mysqli_fetch_array($nresult))
 {
  echo "<EDL>";
  echo "<IdEDL>" . $nrow['IdEDL'] . "</IdEDL>" ;
  echo "<IdComp>" . $nrow['IdComp'] . "/IdComp" ;
  echo "<NomEDL>" . $nrow['NomEDL'] . "</NomEDL>" ;
  echo "<PrenomEDL>" . $nrow['PrenomEDL'] . "</PrenomEDL>" ;
  echo "<Poste>" . $nrow['Poste'] . "</Poste>" ;
  echo "</EDL>";	
}
}
 echo "</Nest>";
mysqli_close($con);
?>