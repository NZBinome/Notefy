<?php
$con=mysqli_connect("localhost","root","root","Tester");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
       $Prenom= $_POST['Prenom'];
$result = mysqli_query($con,"SELECT Prenom FROM Passagers WHERE Prenom='$Prenom'");
echo "<test>";
while($row = mysqli_fetch_array($result))
 {
  echo "<IdVol>" . $row['Prenom'] . "</IdVol>" ;
 }
 echo "</test>";

$test = $_POST['cle'];
//echo $test . ";";
mysqli_close($con);
?>