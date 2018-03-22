--TEST--
CommonMark\Node isset next
--FILE--
<?php
$doc = new CommonMark\Node\Document();
$doc->appendChild($para = new CommonMark\Node\Paragraph);
$doc->appendChild(
	new CommonMark\Node\Paragraph);

$f = function() use($para) {
	return isset($para->next);
};

if ($f() && $f() == $f()) {
	echo "OK";
}
?>
--EXPECT--
OK
