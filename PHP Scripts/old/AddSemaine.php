<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
  $IdProg=$_POST['IdProg'];
  $Jour=$_POST['Jour'];
  $Heure=$_POST['Heure'];
  $Periodicite=$_POST['Periodicite'];
$i=0;

$nentier=mysqli_query($con,"SELECT IdProg FROM Semaine WHERE Heure='$Heure' AND Jour='$Jour'");
while ($row=mysqli_fetch_array($nentier)) {
  if(!is_null($row['IdProg'])){
    $i=1;
    echo "<Nest>";
    echo "<Conflict> On ne peut pas ajouter le jour" . $Jour . "a l'heure" . $Heure ."</Conflict>";
    echo "</Nest>";
}
}
  if($i!=1){

  $entier=mysqli_query($con,"SELECT IdProg FROM Programme WHERE IdProg=(SELECT max(IdProg) FROM Programme)");
while ($rang=mysqli_fetch_array($entier)) {
  $P=$rang['IdProg'];


$sql = "INSERT INTO Semaine (IdProg, Jour, Heure,Periodicite) VALUES ($P,'$Jour','$Heure',$Periodicite)";

if (!mysqli_query($con,$sql))
{
  die('Error: ' . mysqli_error($con));
}
}
}

mysqli_close($con);
?>