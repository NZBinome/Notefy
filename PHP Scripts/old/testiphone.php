<?php
$con=mysqli_connect("localhost","root","root","Blooper");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }
       $Id= $_GET['key'];
       $i=0;
       echo "<Nest>";
       while($i<60){
$result = mysqli_query($con,"SELECT Id,Quote,Title FROM Movies WHERE Id='$Id'");
while($row = mysqli_fetch_array($result)){
	echo "<Movie>";
	echo "<Id>" . $row['Id'] . "</Id>" ;
	echo "<Quote>" . $row['Quote'] . "</Quote>" ;
	echo "<Title>" . $row['Title'] . "</Title>" ;
	//echo $row['Title'];
	echo "</Movie>";
 }
 $Id=$Id+2;
 $i=$i+1;
}
echo "</Nest>";

mysqli_close($con);
?>