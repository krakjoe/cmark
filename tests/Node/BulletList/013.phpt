--TEST--
CommonMark\Node\BulletList invalid isset
--FILE--
<?php
$list = new CommonMark\Node\BulletList;

var_dump(isset($list->something));
?>
--EXPECT--
bool(false)
