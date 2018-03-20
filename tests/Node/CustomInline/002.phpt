--TEST--
CommonMark\Node\CustomInline onEnter
--FILE--
<?php
$node = new CommonMark\Node\CustomInline;

$node->onEnter = "OK";

echo $node->onEnter;
?>
--EXPECT--
OK
