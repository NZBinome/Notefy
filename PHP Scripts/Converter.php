<?php
Class Converter
{
	var $Table;

	function __construct($par)
    {
    	$this->Table=$par;
    }

	function setTable($par)
	{
		$this->Table=$par;
	}

	function getTable()
	{
		return $this->Table;
	}

	function describe()
	{
		$con=mysqli_connect("localhost","root","root","Notefy");
		if (mysqli_connect_errno())
  		{
  			echo "Failed to connect to MySQL: " . mysqli_connect_error();
  		}
  		$describeTable="DESCRIBE " . $this->Table;
		$description = mysqli_query($con,$describeTable);	
		$i=0;
		 while ($column=mysqli_fetch_array($description)) 
 			{
 				$columns[$i]=$column[0];
 				$i=$i+1;
 			}
 		mysqli_close($con);
 		return $columns;
	}

	function select($Keys, $Values)
	{
		$con=mysqli_connect("localhost","root","root","Notefy");
		if (mysqli_connect_errno())
  		{
  			echo "Failed to connect to MySQL: " . mysqli_connect_error();
  		}
		$arguments="";
		$i=0;

		while ($i<count($Keys)) {
			$arguments=$arguments . $Keys[$i] ."=" . $Values[$i];
			if ($i!=count($Keys)-1)
			{
				$arguments=$arguments . " AND ";
			}
			$i=$i+1;
		}

		$query="SELECT * FROM ". $this->Table . " WHERE " . $arguments;
		$result = mysqli_query($con,$query);
		$describeTable="DESCRIBE " . $this->Table;
		$description = mysqli_query($con,$describeTable);	
		$i=0;
		while($row = mysqli_fetch_array($result))
 		{
 			while ($column=mysqli_fetch_array($description)) 
 			{
 				$Results[$i][$column[0]]=$row[$column[0]];
 			}
 			$i=$i+1;
 		}
		mysqli_close($con);
		return $Results;
	}

	function insert($Keys, $Values)
	{
		$con=mysqli_connect("localhost","root","root","Notefy");
		if (mysqli_connect_errno())
  		{
  			echo "Failed to connect to MySQL: " . mysqli_connect_error();
  		}
		$arg1="";
		$arg2="";
		$i=0;

		while ($i<count($Keys)) 
		{
			$arg1=$arg1  . $Keys[$i];
			$arg2=$arg2  . $Values[$i];
			if($i!=count($Keys)-1)
			{
				$arg2=$arg2 . " , ";
				$arg1=$arg1 . " , ";
			}
			$i=$i+1;
		}
		$query="INSERT INTO " . $this->Table . " ( " . $arg1 ." ) VALUES ( " . $arg2 ." )";
		if (!mysqli_query($con,$query))
		{
  			die('Error: ' . mysqli_error($con));
		}
		$max="SELECT max(Id) FROM $this->Table";
		$maxVal = mysqli_query($con,$max);
		$row = mysqli_fetch_array($maxVal);
		return $row['max(Id)'];
		mysqli_close($con);

	}

	function update($Keys,$Values,$ParaKeys,$ParaValues)
	{
		$con=mysqli_connect("localhost","root","root","Notefy");
		if (mysqli_connect_errno())
  		{
  			echo "Failed to connect to MySQL: " . mysqli_connect_error();
  		}
  		$arg1="";
		$arg2="";

		$i=0;
		while ($i<count($Keys)) {
			$arg1=$arg1 . $Keys[$i] . "=" . $Values[$i] . ",";
			$i = $i+1;
		}

		$i=0;
		while ($i<count($ParaKeys)) 
		{
			$arg2=$arg2 . $ParaKeys[$i] . "=" . $ParaValues[$i];
			if ($i!=count($ParaKeys)-1)
			{
				$arg2=$arg2 . " AND ";
			}
			$i=$i+1;
		}


		$arg1=rtrim($arg1,',');
		$query="UPDATE " . $this->Table . " SET " . $arg1 ." WHERE " . $arg2;
		if (!mysqli_query($con,$query))
		{
  			die('Error: ' . mysqli_error($con));
		}
  		mysqli_close($con);

	}

	function delete($Keys,$Values)
	{
		$con=mysqli_connect("localhost","root","root","Notefy");
		if (mysqli_connect_errno())
  		{
  			echo "Failed to connect to MySQL: " . mysqli_connect_error();
  		}
  		$arguments="";
  		$i=0;

		while ($i<count($Keys)) 
		{
			$arguments=$arguments . $Keys[$i] ."=" . $Values[$i];
			if ($i!=count($Keys)-1)
			{
				$arguments=$arguments . " AND ";
			}
			$i=$i+1;
		}

		$query="DELETE FROM ". $this->Table . " WHERE " . $arguments;
		if (!mysqli_query($con,$query))
		{
  			die('Error: ' . mysqli_error($con));
		}
  		mysqli_close($con);

	}

}
?>