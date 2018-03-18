--TEST--
CommonMark\Node\CustomInline onLeave Empty
--FILE--
<?php
$node = new CommonMark\Node\CustomInline;

if (!$node->getOnLeave()) {
	echo "OK";
}
?>
--EXPECT--
OK
