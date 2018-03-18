--TEST--
CommonMark\Node\CustomBlock onEnter
--FILE--
<?php
$node = new CommonMark\Node\CustomBlock;

$node->setOnEnter("OK");

echo $node->getOnEnter();
?>
--EXPECT--
OK
