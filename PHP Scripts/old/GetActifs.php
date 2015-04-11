<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
       $IdVol= $_POST['IdVol'];
$result = mysqli_query($con,"SELECT * FROM Vol WHERE EtatVol='Actif' Or EtatVol='Retarde'");
echo "<Nest>";
while($row = mysqli_fetch_array($result))
 {
  $k=$row['IdProg'];
  $nresult = mysqli_query($con,"SELECT Code FROM Programme WHERE IdProg='$k'");
  while($nrow = mysqli_fetch_array($nresult))
 {
  echo "<Vol>";
  echo "<IdVol>" . $row['IdVol'] . "</IdVol>" ;
  echo "<IdEquipe>" . $row['IdEquipe'] . "</IdEquipe>" ;
  echo "<IdEq>" . $row['IdEq'] . "</IdEq>" ;
  echo "<IdProg>" . $k . "</IdProg>" ;
  echo "<IdAvion>" . $row['IdAvion'] . "</IdAvion>" ;
  echo "<DatPreVol>" . $row['DatPreVol'] . "</DatPreVol>" ;
  echo "<HeurPreVol>" . $row['HeurPreVol'] . "</HeurPreVol>" ;
  echo "<DatReVol>" . $row['DatReVol'] . "</DatReVol>" ;
  echo "<HeurReVol>" . $row['HeurReVol'] . "</HeurReVol>" ;
  echo "<EtatVol>" . $row['EtatVol'] . "</EtatVol>" ;
  echo "<Code>" .  $nrow['Code'] . "</Code>" ;
}
  echo "</Vol>";
 }
 echo "</Nest>";

mysqli_close($con);
?>