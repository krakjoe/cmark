--TEST--
CommonMark\Node\CustomBlock onLeave
--FILE--
<?php
$node = new CommonMark\Node\CustomBlock;

$node->setOnLeave("OK");

echo $node->getOnLeave();
?>
--EXPECT--
OK
