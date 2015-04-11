<?php
$con=mysqli_connect("localhost","root","root","Projet");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
       $IdVol= $_POST['IdVol'];
$result = mysqli_query($con,"SELECT * FROM Rapport WHERE IdRapport='$IdRapport'");
echo "<Nest>";
while($row = mysqli_fetch_array($result))
 {
  echo "<Rapport>";
  echo "<IdRapport>" . $row['IdRapport'] . "</IdRapport>" ;
  echo "<IdEquipe>" . $row['IdEquipe'] . "</IdEquipe>" ;
  echo "<IdAvion>" . $row['IdAvion'] . "</IdAvion>" ;
  echo "<IdVol>" . $row['IdVol'] . "</IdVol>" ;
  echo "<DateRap>" . $row['DateRap'] . "</DateRap>" ;
  echo "</Rapport>";
 }
 echo "</Nest>";

mysqli_close($con);
?>