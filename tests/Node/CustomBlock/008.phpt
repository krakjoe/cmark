--TEST--
CommonMark\Node\CustomBlock clone
--FILE--
<?php
$doc = new CommonMark\Node\Document;

$node = new CommonMark\Node\CustomBlock;
$node->onEnter = "ENTER";
$node->onLeave = "LEAVE";
$node->appendChild(
	new CommonMark\Node\Text("NODE"));

$doc->appendChild($node);

var_dump($doc, clone $doc);
?>
--EXPECT--
object(CommonMark\Node\Document)#1 (1) {
  ["children"]=>
  array(1) {
    [0]=>
    object(CommonMark\Node\CustomBlock)#4 (3) {
      ["enter"]=>
      string(5) "ENTER"
      ["leave"]=>
      string(5) "LEAVE"
      ["children"]=>
      array(1) {
        [0]=>
        object(CommonMark\Node\Text)#5 (1) {
          ["literal"]=>
          string(4) "NODE"
        }
      }
    }
  }
}
object(CommonMark\Node\Document)#3 (1) {
  ["children"]=>
  array(1) {
    [0]=>
    object(CommonMark\Node\CustomBlock)#4 (3) {
      ["enter"]=>
      string(5) "ENTER"
      ["leave"]=>
      string(5) "LEAVE"
      ["children"]=>
      array(1) {
        [0]=>
        object(CommonMark\Node\Text)#5 (1) {
          ["literal"]=>
          string(4) "NODE"
        }
      }
    }
  }
}

