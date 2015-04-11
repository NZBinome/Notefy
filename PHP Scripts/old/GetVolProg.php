<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
       $IdProg= $_POST['IdProg'];
$result = mysqli_query($con,"SELECT * FROM Vol WHERE IdProg='$IdProg' AND EtatVol='Actif'");
echo "<Nest>";
while($row = mysqli_fetch_array($result))
 {
  echo "<Vol>";
  echo "<IdVol>" . $row['IdVol'] . "</IdVol>" ;
  echo "<IdEquipe>" . $row['IdEquipe'] . "</IdEquipe>" ;
  echo "<IdEq>" . $row['IdEq'] . "</IdEq>" ;
  echo "<IdProg>" . $row['IdProg'] . "</IdProg>" ;
  echo "<IdAvion>" . $row['IdAvion'] . "</IdAvion>" ;
  echo "<DatPreVol>" . $row['DatPreVol'] . "</DatPreVol>" ;
  echo "<HeurPreVol>" . $row['HeurPreVol'] . "</HeurPreVol>" ;
  echo "<DatReVol>" . $row['DatReVol'] . "</DatReVol>" ;
  echo "<HeurReVol>" . $row['HeurReVol'] . "</HeurReVol>" ;
  echo "<EtatVol>" . $row['EtatVol'] . "</EtatVol>" ;
  echo "</Vol>";
 }
 echo "</Nest>";

mysqli_close($con);
?>