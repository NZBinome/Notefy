<?php

include 'Converter.php';



class Follows
{
	var $Follower;
	var $Followed;
	var $Date;
	var $Converter;
	var $columns;

	function __construct()
	{
		$this->Converter = new Converter("Follows");
		$this->columns=$this->Converter->describe();
	}

	function setFollower($par)
	{
		$this->Follower=$par;
	}

	function setFollowed($par)
	{
		$this->Followed=$par;
	}

	function setDate($par)
	{
		$this->Date=date("Y-m-d",strtotime($par));
	}

	function getFollower()
	{
		return $this->Follower;
	}

	function getFollowed()
	{
		return $this->Followed;
	}

	function getDate()
	{
		return $this->Date;
	}

	function insert()
	{
		$i=0;
        while ($i<count($this->columns)) 
        {
            $Keys[$i]=$this->columns[$i];
            $i=$i+1;
        }
		$Values = array($this->Follower,$this->Followed,"'$this->Date'");
		$this->Converter->insert($Keys,$Values);
	}

	function update()
	{
		$Keys = array($this->columns[2]);
		$Values = array("'$this->Date'");
		$ParaKeys = array($this->columns[0],$this->columns[1]);
		$ParaValues = array($this->Follower,$this->Followed);
		$this->Converter->update($Keys,$Values,$ParaKeys,$ParaValues);
	}

	function select()
	{
		$Keys = array($this->columns[0],$this->columns[1]);
		$Values = array($this->Follower,$this->Followed);
		$Results=$this->Converter->select($Keys,$Values);
      	$i=0;
      	while ($i<count($Results)) 
      	{
      		$this->Date=$Results[$i][$this->columns[2]];
      		$i=$i+1;
      	}
	}

	function delete()
	{
		$Keys = array($this->columns[0],$this->columns[1]);
		$Values = array($this->Follower,$this->Followed);
		$this->Converter->delete($Keys,$Values);
	}

	function display()
	{
		echo "Follows <br/>";
		echo "Follower : " . $this->Follower . "<br/>";
		echo "Followed : " . $this->Followed . "<br/>";
		echo "Date : " . $this->Date . "<br/>";
	}


}
?>