<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
       $IdModele= $_POST['IdModele'];
$result = mysqli_query($con,"SELECT * FROM Modele WHERE IdModele='$IdModele'");
echo "<Nest>";
while($row = mysqli_fetch_array($result))
 {
  echo "<Modele>";
  echo "<IdModele>" . $row['IdModele'] . "</IdModele>" ;
  echo "<Reservoire>" . $row['Reservoire'] . "</Reservoire>" ;
  echo "<DistMax>" . $row['DistMax'] . "</DistMax>" ;
  echo "<VitCrois>" . $row['VitCrois'] . "</VitCrois>" ;
  echo "<NomModel>" . $row['NomModel'] . "</NomModel>" ;
  echo "</Modele>";
 }
 echo "</Nest>";

mysqli_close($con);
?>