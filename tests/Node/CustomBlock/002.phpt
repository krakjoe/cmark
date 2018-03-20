--TEST--
CommonMark\Node\CustomBlock onEnter
--FILE--
<?php
$node = new CommonMark\Node\CustomBlock;

$node->onEnter = "OK";

echo $node->onEnter;
?>
--EXPECT--
OK
