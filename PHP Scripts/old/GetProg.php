<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
       $IdProg= $_POST['IdProg'];
$result = mysqli_query($con,"SELECT * FROM Programme WHERE IdProg='$IdProg'");
echo "<Nest>";
while($row = mysqli_fetch_array($result))
 {
  echo "<Prog>";
  echo "<IdProg>" . $row['IdProg'] . "</IdProg>" ;
  echo "<IdAvion>" . $row['IdAvion'] . "</IdAvion>" ;
  echo "<IdEquipe>" . $row['IdEquipe'] . "</IdEquipe>" ;
  echo "<NumAero>" . $row['NumAero'] . "</NumAero>" ;
  echo "<IdEq>" . $row['IdEq'] . "</IdEq>" ;
  echo "<Code>" . $row['Code'] . "</Code>" ;
  echo "<Direction>" . $row['Direction'] . "</Direction>" ;
  echo "<DateDebut>" . $row['DateDebut'] . "</DateDebut>" ;
  echo "<DateFin>" . $row['DateFin'] . "</DateFin>" ;
  echo "<Duree>" . $row['Duree'] . "</Duree>" ;
  echo "</Prog>";
 }
 echo "</Nest>";

mysqli_close($con);
?>