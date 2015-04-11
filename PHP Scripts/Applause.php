<?php


class Applause
{
	var $Spectator;
	var $Melody;
	var $Date;
	var $Key_Spectator;
	var $Key_Melody;
	var $Key_Date;
	var $Converter;

	function __construct() 
    { 
        $a = func_get_args(); 
        $i = func_num_args(); 
        if (method_exists($this,$f='__construct'.$i)) { 
            call_user_func_array(array($this,$f),$a); 
        } 
    }

    function __construct2($User,$Melody)
    {
      $this->__construct0();
      $this->Spectator=$User;
      $this->Melody=$Melody;
      $this->select();
    }

    function __construct0()
    {
      $this->Converter=new Bridge("Applause");
      $this->setKeys();
    }

    function setKeys()
    {
    	$this->Key_Spectator=$this->Converter->Attributes[0];
    	$this->Key_Melody=$this->Converter->Attributes[1];
    	$this->Key_Date=$this->Converter->Attributes[2];
    }

	function setSpectator($par)
	{
		$this->Spectator=$par;
	}

	function setMelody($par)
	{
		$this->Melody=$par;
	}

	function setDate($par)
	{
		$this->Date=date("Y-m-d H:i:s",strtotime($par));
	}

	function getSpectator()
	{
		return $this->Spectator;
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
        $Keys[0]=$this->Key_Spectator;
        $Keys[1]=$this->Key_Melody;
        $Keys[2]=$this->Key_Date;
		$Values = array($this->Spectator,$this->Melody,"'$this->Date'");
		$this->Converter->insert($Keys,$Values);
	}

	function update()
	{
		$Keys = array($this->Key_Date);
		$Values = array("'$this->Date'");
		$ParaKeys = array($this->Key_Spectator,$this->Key_Melody);
		$ParaValues = array($this->Spectator,$this->Melody);
		$this->Converter->update($Keys,$Values,$ParaKeys,$ParaValues);
	}

	function setApplause($Result)
	{
		$this->Spectator=$Result[$this->Key_Spectator];
		$this->Melody=$Result[$this->Key_Melody];
		$this->Date=$Result[$this->Key_Date];
	}

	function select()
	{
		$Keys = array($this->Key_Spectator,$this->Key_Melody);
		$Values = array($this->Spectator,$this->Melody);
		$Results=$this->Converter->select($Keys,$Values);
		$this->setApplause($Results[0]);
      	$i=1;
      	while ($i<count($Results)) 
      	{
      		$this->setApplause($Results[$i]);
      		$i=$i+1;
      	}
	}

	function delete()
	{
		$Keys = array($this->Key_Spectator,$this->Key_Melody);
		$Values = array($this->Spectator,$this->Melody);
		$this->Converter->delete($Keys,$Values);
	}

	function display()
	{
		echo "Applause <br/>";
		echo "Spectator : " . $this->Spectator . "<br/>";
		echo "Melody : " . $this->Melody . "<br/>";
		echo "Date : " . $this->Date . "<br/>";
	}

	function toXML()
	{
		$echo = "<Applause>";
      	$echo = $echo . "<Spectator>" . $this->Spectator . "</Spectator>";
      	$echo = $echo . "<Melody>" . $this->Melody . "</Melody>";
      	$echo = $echo . "<Date>" . $this->Date . "</Date>";
      	$echo = $echo . "</Applause>";
      	return $echo ;
	}


}
?>