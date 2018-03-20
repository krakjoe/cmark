--TEST--
CommonMark\Node\CustomInline onLeave Empty
--FILE--
<?php
$node = new CommonMark\Node\CustomInline;

if (!$node->onLeave) {
	echo "OK";
}
?>
--EXPECT--
OK
