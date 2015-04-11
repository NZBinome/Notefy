<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
       $IdComp= $_POST['IdComp'];
$result = mysqli_query($con,"SELECT * FROM Compagnie WHERE IdComp='$IdComp'");
echo "<Nest>";
while($row = mysqli_fetch_array($result))
 {
  echo "<Compagnie>";
  echo "<IdComp>" . $row['IdComp'] . "</IdComp>" ;
  echo "<NomComp>" . $row['NomComp'] . "</NomComp>" ;
  echo "<Origine>" . $row['Origine'] . "</Origine>" ;
  echo "</Compagnie>";
 }
 echo "</Nest>";

mysqli_close($con);
?>