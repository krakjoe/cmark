--TEST--
CommonMark\Node\CustomInline onEnter
--FILE--
<?php
$node = new CommonMark\Node\CustomInline;

$node->setOnEnter("OK");

echo $node->getOnEnter();
?>
--EXPECT--
OK
