<?php

include 'Converter.php';



class Share
{
	var $Sharer;
	var $Melody;
	var $Date;
	var $Converter;
	var $columns;

	function __construct()
	{
		$this->Converter = new Converter("Share");
		$this->columns=$this->Converter->describe();	}

	function setSharer($par)
	{
		$this->Sharer=$par;
	}

	function setMelody($par)
	{
		$this->Melody=$par;
	}

	function setDate($par)
	{
		$this->Date=date("Y-m-d",strtotime($par));
	}

	function getSharer()
	{
		return $this->Sharer;
	}

	function getMelody()
	{
		return $this->Melody;
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
		$Values = array($this->Sharer,$this->Melody,"'$this->Date'");
		$this->Converter->insert($Keys,$Values);
	}

	function update()
	{
		$Keys = array($this->columns[2]);
		$Values = array("'$this->Date'");
		$ParaKeys = array($this->columns[0],$this->columns[1]);
		$ParaValues = array($this->Sharer,$this->Melody);
		$this->Converter->update($Keys,$Values,$ParaKeys,$ParaValues);
	}

	function select()
	{
		$Keys = array($this->columns[0],$this->columns[1]);
		$Values = array($this->Sharer,$this->Melody);
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
		$Values = array($this->Sharer,$this->Melody);
		$this->Converter->delete($Keys,$Values);
	}

	function display()
	{
		echo "Share <br/>";
		echo "Sharer : " . $this->Sharer . "<br/>";
		echo "Melody : " . $this->Melody . "<br/>";
		echo "Date : " . $this->Date . "<br/>";
	}


}
?>