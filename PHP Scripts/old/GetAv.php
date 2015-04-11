<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
       $IdAvion= $_POST['Id'];
$result = mysqli_query($con,"SELECT * FROM Avion");
echo "<Nest>";
while($row = mysqli_fetch_array($result))
 {
  echo "<Avion>";
  echo "<IdAvion>" . $row['IdAvion'] . "</IdAvion>" ;
  echo "<IdModele>" . $row['IdModele'] . "</IdModele>" ;
  echo "<IdComp>" . $row['IdComp'] . "</IdComp>" ;
  echo "<IdAvCom>" . $row['IdAvCom'] . "</IdAvCom>" ;
  echo "<Gare>" . $row['Gare'] . "</Gare>" ;
  echo "</Avion>";
 }
 echo "</Nest>";

mysqli_close($con);
?>