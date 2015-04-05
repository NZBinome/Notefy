<?php
$con=mysqli_connect("localhost","root","root","Notefy");
if (mysqli_connect_errno())
  {
  echo "Failed to connect to MySQL: " . mysqli_connect_error();
  }

$Command = $_GET['Command'];
$Table = $_GET['Table'];
$Length = $_GET['Length'];

$i=1;

echo "jjj";

// The Select command only works if the parameters we are using to select the row are Integers.

if ($Command=="SELECT")
{
	$arguments="";
	while ($i<=$Length) 
	{
		$IdArg="Id" . $i;
		$ValueArg="Value" . $i;
		$arguments=$arguments . $_GET[$IdArg] ."=" . $_GET[$ValueArg];
		if ($i!=$Length)
		{
			$arguments=$arguments . " AND ";
		}
		$i=$i+1;
	}

	$query="SELECT * FROM ". $Table . " WHERE " . $arguments;
	$result = mysqli_query($con,$query);
	$describeTable="DESCRIBE " . $Table;
	$description = mysqli_query($con,$describeTable);
	echo "<$Table>";
	
	while($row = mysqli_fetch_array($result))
 	{
 		while ($column=mysqli_fetch_array($description)) {
 			echo "<$column[0]>" . $row[$column[0]] . "</$column[0]>";
 		}
 	}
 	echo "</$Table>";
}

if ($Command=="INSERT")
{
	$arg1="";
	$arg2="";
	while ($i<=$Length) 
	{
		$IdArg="Id" . $i;
		$ValueArg="Value" . $i;
		$arg1=$arg1  . $_GET[$IdArg];
		$arg2=$arg2  . $_GET[$ValueArg];
		if($i!=$Length)
		{
			$arg2=$arg2 . " , ";
			$arg1=$arg1 . " , ";
		}
		$i=$i+1;
	}
	$query="INSERT INTO " . $Table . " ( " . $arg1 ." ) VALUES ( " . $arg2 ." )";
	echo $query;
	if (!mysqli_query($con,$query))
{
  die('Error: ' . mysqli_error($con));
}
}

// UPDATE only updates strings where the parameters are Integers

if ($Command=="UPDATE")
{
	$arg1="";
	$arg2="";
	while ($i<=$Length) {
		$IdArg="Id" . $i;
		$ValueArg="Value" . $i;
		if($_GET[$IdArg]=="Id")
		{
			$arg2=$_GET[$IdArg] . "=" . $_GET[$ValueArg];
		}
		else
		{
			$arg1=$arg1 . $_GET[$IdArg] . "='" . $_GET[$ValueArg] . "',";
		}

		$i = $i+1;
	}
	$arg1=rtrim($arg1,',');
	$query="UPDATE " . $Table . " SET " . $arg1 ." WHERE " . $arg2;
	if (!mysqli_query($con,$query))
	{
  		die('Error: ' . mysqli_error($con));
	}
}

if ($Command=="DELETE") 
{	
	$arguments="";
	while ($i<=$Length) 
	{
		$IdArg="Id" . $i;
		$ValueArg="Value" . $i;
		$arguments=$arguments . $_GET[$IdArg] ."=" . $_GET[$ValueArg];
		if ($i!=$Length)
		{
			$arguments=$arguments . " AND ";
		}
		$i=$i+1;
	}

	$query="DELETE FROM ". $Table . " WHERE " . $arguments;
	echo $query;
	if (!mysqli_query($con,$query))
	{
  		die('Error: ' . mysqli_error($con));
	}
}

mysqli_close($con);
?>