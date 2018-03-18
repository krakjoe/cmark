--TEST--
CommonMark\Node\CustomInline onLeave
--FILE--
<?php
$node = new CommonMark\Node\CustomInline;

$node->setOnLeave("OK");

echo $node->getOnLeave();
?>
--EXPECT--
OK
