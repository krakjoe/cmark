--TEST--
CommonMark\Node isset parent
--FILE--
<?php
$doc = new CommonMark\Node\Document();
$doc->appendChild(
	$para = new CommonMark\Node\Paragraph);

$f = function() use($para) {
	return isset($para->parent);
};

if ($f() == $f()) {
	echo "OK";
}
?>
--EXPECT--
OK
