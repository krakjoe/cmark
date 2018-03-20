--TEST--
CommonMark\Node\BulletList Tight Errors
--FILE--
<?php
$list = new CommonMark\Node\BulletList;

try {
	$list->tight = [];
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
