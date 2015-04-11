<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
       $IdVol= $_POST['IdVol'];
$result = mysqli_query($con,"SELECT * FROM Vol");
echo "<Nest>";
while($row = mysqli_fetch_array($result))
 {
  $V=$row['IdProg'];
  $nresult = mysqli_query($con,"SELECT Code,NumAero FROM Programme WHERE IdProg='$V'");
while($nrow = mysqli_fetch_array($nresult))
 {
    $n=$nrow['NumAero'];
     $nnresult = mysqli_query($con,"SELECT NomAero FROM Aeroport WHERE NumAero='$n'");
while($nnrow = mysqli_fetch_array($nnresult))
 {
    echo "<Vol>";
  echo "<IdVol>" . $row['IdVol'] . "</IdVol>" ;
  echo "<IdEquipe>" . $row['IdEquipe'] . "</IdEquipe>" ;
  echo "<IdEq>" . $row['IdEq'] . "</IdEq>" ;
  echo "<IdProg>" . $V . "</IdProg>" ;
  echo "<IdAvion>" . $row['IdAvion'] . "</IdAvion>" ;
  echo "<DatPreVol>" . $row['DatPreVol'] . "</DatPreVol>" ;
  echo "<HeurPreVol>" . $row['HeurPreVol'] . "</HeurPreVol>" ;
  echo "<DatReVol>" . $row['DatReVol'] . "</DatReVol>" ;
  echo "<HeurReVol>" . $row['HeurReVol'] . "</HeurReVol>" ;
  echo "<EtatVol>" . $row['EtatVol'] . "</EtatVol>" ;
  echo "<Code>" . $nrow['Code'] . "</Code>" ;
  echo "<NomAero>" . $nnrow['NomAero'] . "</NomAero>";
  echo "</Vol>";
 }
 }
 }
 echo "</Nest>";

mysqli_close($con);
?>