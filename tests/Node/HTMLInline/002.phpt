--TEST--
CommonMark\Node fetch HTMLInline
--FILE--
<?php
$md = <<<MD
some <html>inline</html>
MD;

$parser = new CommonMark\Parser();

$parser->parse($md);

$doc = $parser->finish();

$para = $doc->firstChild;

$code = $para->firstChild->next;

if ($para instanceof CommonMark\Node\Paragraph &&
    $code instanceof CommonMark\Node\HTMLInline) {
	echo "OK";
}
?>
--EXPECT--
OK
