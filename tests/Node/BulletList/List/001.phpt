--TEST--
CommonMark\Node\BulletList Tight
--FILE--
<?php
$list = new CommonMark\Node\BulletList;

$list->tight = true;

if ($list->tight) {
	echo "OK";
}
?>
--EXPECT--
OK
