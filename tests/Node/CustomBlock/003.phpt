--TEST--
CommonMark\Node\CustomBlock onLeave
--FILE--
<?php
$node = new CommonMark\Node\CustomBlock;

$node->onLeave = "OK";

echo $node->onLeave;
?>
--EXPECT--
OK
