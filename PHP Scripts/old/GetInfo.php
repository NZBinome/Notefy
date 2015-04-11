<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
       $Jour = $_POST['Jour'];
       $Date=$_POST['DatPreVol'];


$entier=mysqli_query($con,"SELECT IdVol FROM Vol WHERE IdVol=(SELECT max(IdVol) FROM Vol)");
while ($rang=mysqli_fetch_array($entier)) {
  $a=$rang['IdVol'];
}

//echo $a . ";" ;

$result = mysqli_query($con,"SELECT IdProg,Heure,Periodicite,Compte FROM Semaine WHERE Jour='$Jour'");

while($row = mysqli_fetch_array($result))
 {

 	$a=$a+1;
  $Prog=$row['IdProg'];
  $IdHeure=$row['Heure']; 
  echo $Jour . ";" . $Prog ;
  
  if($row['Compte']==$row['Periodicite']){

  $nresult=mysqli_query($con,"SELECT IdAvion,IdEquipe,IdEq,DateFin FROM Programme Where IdProg='$Prog'");
  while ($nrow=mysqli_fetch_array($nresult)) {
  
	$Avion=$nrow['IdAvion'];
  $Equipe=$nrow['IdEquipe'];
  $Eq=$nrow['IdEq'];
  $DateFin=$nrow['DateFin'];

    if($Date > $DateFin){
        die('Error: ' . mysqli_error($con));
    }


  	$sql = "INSERT INTO Vol (IdVol,IdEquipe, IdEq,IdProg, IdAvion, DatPreVol, HeurPreVol, EtatVol) VALUES ($a,$Equipe,$Eq,$Prog,$Avion,'$Date','$IdHeure','Attente')";

  mysqli_query($con,"UPDATE Semaine SET Compte='1' WHERE Jour='$Jour' AND IdProg='$Prog' AND Heure='$IdHeure'");

if (!mysqli_query($con,$sql))
{
  die('Error: ' . mysqli_error($con));
}
  }
}
else{
  $iCompte=$row['Compte']+1;
  mysqli_query($con,"UPDATE Semaine SET Compte='$iCompte' WHERE Jour='$Jour' AND IdProg='$Prog' AND Heure='$IdHeure'");
}
 }
mysqli_close($con);
?>