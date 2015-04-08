<?php
Class Bridge
{
	var $Table;
	var $Attributes;
	var $con;


    function __construct() 
    { 
        $a = func_get_args(); 
        $i = func_num_args(); 
        if (method_exists($this,$f='__construct'.$i)) { 
            call_user_func_array(array($this,$f),$a); 
        } 
    }

    function __construct1($Table)
    {
      $this->Table=$Table;
      $this->setAttributes();
    }

    function __construct0()
    {
    }

	function setTable($par)
	{
		$this->Table=$par;
		$this->setAttributes();
	}

	function getTable()
	{
		return $this->Table;
	}

	function describe()
	{
		$this->openConnection();
  		$describeTable="DESCRIBE " . $this->Table;
		$description = mysqli_query($this->con,$describeTable);	
		$i=0;
		 while ($column=mysqli_fetch_array($description)) 
 			{
 				$columns[$i]=$column[0];
 				$i=$i+1;
 			}
 		$this->closeConnection();
 		return $columns;
	}

	function openConnection()
	{
		$this->con=mysqli_connect("localhost","root","root","Notefy");
		if (mysqli_connect_errno())
  		{
  			echo "Failed to connect to MySQL: " . mysqli_connect_error();
  		}
	}

	function closeConnection()
	{
		mysqli_close($this->con);
	}

	function select($Keys, $Values)
	{
		$this->openConnection();
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
		$result = mysqli_query($this->con,$query);
		$i=0;
		while($row = mysqli_fetch_array($result))
 		{
 			$describeTable="DESCRIBE " . $this->Table;
			$description = mysqli_query($this->con,$describeTable);	
 			while ($column=mysqli_fetch_array($description)) 
 			{
 				$Results[$i][$column[0]]=$row[$column[0]];
 			}
 			$i=$i+1;
 		}
		$this->closeConnection();
		return $Results;
	}

	function insert($Keys, $Values)
	{
		$this->openConnection();
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
		if (!mysqli_query($this->con,$query))
		{
  			die('Error: ' . mysqli_error($this->con));
		}
		$max="SELECT max(Id) FROM $this->Table";
		$maxVal = mysqli_query($this->con,$max);
		$row = mysqli_fetch_array($maxVal);
		$this->closeConnection();
		return $row['max(Id)'];
	}

	function update($Keys,$Values,$ParaKeys,$ParaValues)
	{
		$this->openConnection();
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
		if (!mysqli_query($this->con,$query))
		{
  			die('Error: ' . mysqli_error($this->con));
		}
  		$this->closeConnection();
	}

	function delete($Keys,$Values)
	{
		$this->openConnection();
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
		if (!mysqli_query($this->con,$query))
		{
  			die('Error: ' . mysqli_error($this->con));
		}
  		$this->closeConnection();

	}

	function setAttributes()
	{
      	$columns=$this->describe();
      	if ($this->Table=="Users") 
      	{
      		$this->Attributes[0]=$columns[0]; //Id
      		$this->Attributes[1]=$columns[1]; //First Name
      		$this->Attributes[2]=$columns[2]; //Last Name
      		$this->Attributes[3]=$columns[3]; //Stage Name
      		$this->Attributes[4]=$columns[4]; //Picture Link
      		$this->Attributes[5]=$columns[5]; //Birthday
      	}

      	if ($this->Table=="Melodies") 
      	{
      		$this->Attributes[0]=$columns[0]; //Id
      		$this->Attributes[1]=$columns[1]; //File Link
      		$this->Attributes[2]=$columns[2]; //Title
      		$this->Attributes[3]=$columns[3]; //Date
      		$this->Attributes[4]=$columns[4]; //User Id
      	}

      	if ($this->Table=="Applause") 
      	{
      		$this->Attributes[0]=$columns[0]; //Spectator
      		$this->Attributes[1]=$columns[1]; //Melody
      		$this->Attributes[2]=$columns[2]; //Date
      	}

      	if ($this->Table=="Comment")
      	{
      		$this->Attributes[0]=$columns[0]; //Id
      		$this->Attributes[1]=$columns[1]; //Writer
      		$this->Attributes[2]=$columns[2]; //Melody
      		$this->Attributes[3]=$columns[3]; //Script
      		$this->Attributes[4]=$columns[4]; //Date
      	}

      	if ($this->Table=="Follows") {
      		$this->Attributes[0]=$columns[0]; //Follower
      		$this->Attributes[1]=$columns[1]; //Followed
      		$this->Attributes[2]=$columns[2]; //Date
      	}

      	if ($this->Table=="Share") {
      		$this->Attributes[0]=$columns[0]; //Sharer
      		$this->Attributes[1]=$columns[1]; //Melody
      		$this->Attributes[2]=$columns[2]; //Date
      	}
	}

}
?>