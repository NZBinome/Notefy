<?php

include ('Converter.php');

class  Comment
{
    var $Id;
    var $Writer;
    var $Melody;
    var $Comment;
    var $Date;
    var $Converter;
    var $columns;

    function __construct()
    {
      $this->Converter=new Converter("Comment");
      $this->columns=$this->Converter->describe();
    }

    function setId($par)
    {
      $this->Id=$par;
    }

    function setWriter($par)
    {
       $this->Writer = $par;
    }

    function setMelody($par)
    {
       $this->Melody = $par;
    }

    function setComment($par)
    {
       $this->Comment = $par;
    }

    function setDate($par)
    {
      $this->Date=date("Y-m-d",strtotime($par));
    }

    function getId()
    {
      return $this->Id;
    }

    function getWriter()
    {
       return $this->Writer;
    }

    function getMelody()
    {
       return $this->Melody;
    }

    function getComment()
    {
       return $this->Comment;
    }

    function getDate()
    {
      return $this->Date;
    }

    function select()
    {
      $Keys = array($this->columns[0]);
      $Values = array($this->Id);
      $Results=$this->Converter->select($Keys,$Values);
      $i=0;
      while ($i<count($Results)) 
      {
        $this->Writer=$Results[$i][$this->columns[1]];
        $this->Melody=$Results[$i][$this->columns[2]];
        $this->Comment=$Results[$i][$this->columns[3]];
        $this->Date=$Results[$i][$this->columns[4]];
        $i=$i+1;
      }
    }

    function insert()
    {
      $i=0;
      while ($i<count($this->columns)-1) {
        $Keys[$i]=$this->columns[$i+1];
        $i=$i+1;
      }
      $Values = array("'$this->Writer'","'$this->Melody'","'$this->Comment'","'$this->Date'");
      $this->Id = $this->Converter->insert($Keys,$Values);
    }

    function update()
    {
      $i=0;
      while ($i<count($this->columns)-1) {
        $Keys[$i]=$this->columns[$i+1];
        $i=$i+1;
      }
      $Values = array("'$this->Writer'","'$this->Melody'","'$this->Comment'","'$this->Date'");
      $ParaKeys=array($this->columns[0]);
      $ParaValues=array("$this->Id");
      $this->Converter->update($Keys,$Values,$ParaKeys,$ParaValues);
    }

    function delete()
    {
      $Keys = array($this->columns[0]);
      $Values = array($this->Id);
      $this->Converter->delete($Keys,$Values);
    }

    function display()
    {
      echo "User <br/>";
      echo "Id : " . $this->Id . "<br/>";
      echo "Writer : " . $this->Writer . "<br/>";
      echo "Melody : " . $this->Melody . "<br/>";
      echo "Comment : " . $this->Comment . "<br/>";
      echo "Date : " . $this->Date . "<br/>";
    }

}
?>