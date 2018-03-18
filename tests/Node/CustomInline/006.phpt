--TEST--
CommonMark\Node\CustomInline onEnter Empty
--FILE--
<?php
$node = new CommonMark\Node\CustomInline;

if (!$node->getOnEnter()) {
	echo "OK";
}
?>
--EXPECT--
OK
