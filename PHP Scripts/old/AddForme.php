<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "<erreure>" . "Impossible d'ouvrir la base de donnees" . "</erreure>";
  }

  $IdEquipe=$_POST['IdEquipe'];
  $IdPDM=$_POST['IdPDM'];

$sql = "INSERT INTO forme (IdPDM, IdEquipe) VALUES ($IdPDM, $IdEquipe)";

if (!mysqli_query($con,$sql))
{
  die('Error: ' . mysqli_error($con));
}
mysqli_close($con);
?>